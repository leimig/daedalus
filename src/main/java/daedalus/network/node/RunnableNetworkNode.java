package daedalus.network.node;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import daedalus.network.node.cache.ContentStore;
import daedalus.network.protocol.DataPacket;
import daedalus.network.protocol.InterestPacket;

public class RunnableNetworkNode implements NetworkNode, Runnable {

	private List<Request> requests;
	
	private List<NetworkNode> forwardingNodes;
	
	private Map<String, List<NetworkNode>> pendingInterestTable;
	
	private ContentStore contentStore; 
	
	public RunnableNetworkNode(List<NetworkNode> forwardingNodes, ContentStore contentStore) {
		this.requests = new LinkedList<>();

		this.forwardingNodes = forwardingNodes;
		this.pendingInterestTable = new HashMap<>();
		this.contentStore = contentStore;
	}

	@Override
	public void lookup(NetworkNode requester, InterestPacket packet) {
		this.requests.add(new LookupRequest(requester, packet));
	}

	@Override
	public void receive(NetworkNode sender, DataPacket packet) {
		this.requests.add(new ResponseRequest(sender, packet));
	}
	
	@Override
	public void run() {
		while (true) {
			if (this.requests.isEmpty()) {
				Thread.yield();
			}
			
			Request request = this.requests.remove(0);
			
			if (request instanceof LookupRequest) { // Some node requested a DataPacket through an InterestPacket
				DataPacket packet = this.contentStore.lookup(request.getPacket().getIdentifier());
				
				if (packet == null) {
					this.forwardInterestPacket((InterestPacket) request.getPacket());
				} else {
					request.getSender().receive(this, packet);
				}
			
			} else if (request instanceof ResponseRequest) { // Some node sent a DataPacket answering an InterestPacket
				this.forwardDataPacket((DataPacket) request.getPacket());
			}
			
			Thread.yield();
		}
	}
	
	private void forwardInterestPacket(InterestPacket packet) {
		for (Iterator<NetworkNode> iterator = forwardingNodes.iterator(); iterator.hasNext();) {
			NetworkNode networkNode = (NetworkNode) iterator.next();
			networkNode.lookup(this, packet);
		}
	}
	
	private void forwardDataPacket(DataPacket packet) {
		List<NetworkNode> networkNodes = this.pendingInterestTable.remove(packet.getIdentifier());
		
		if (networkNodes != null) {					
			for (Iterator<NetworkNode> iterator = networkNodes.iterator(); iterator.hasNext();) {
				NetworkNode networkNode = (NetworkNode) iterator.next();
				networkNode.receive(this, packet);
			}
		}
	}
}
