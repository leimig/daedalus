package daedalus.network.node;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import daedalus.network.protocol.DataPacket;
import daedalus.network.protocol.InterestPacket;

public class RunnableNetworkNode implements NetworkNode, Runnable {

	private List<Request> requests;
	
	private List<NetworkNode> forwardingNodes;
	
	private Map<String, List<NetworkNode>> pendingInterestTable;
	
	public RunnableNetworkNode(List<NetworkNode> forwardingNodes) {
		this.requests = new LinkedList<>();

		this.forwardingNodes = forwardingNodes;
		this.pendingInterestTable = new HashMap<>();
	}
	
	@Override
	public void run() {
		while (true) {
			if (this.requests.isEmpty()) {
				Thread.yield();
			}
			
			Request storedPacket = this.requests.remove(0);
			
			if (storedPacket instanceof LookupRequest) {
				
			} else if (storedPacket instanceof ResponseRequest) {
				List<NetworkNode> networkNodes = this.pendingInterestTable.remove(storedPacket.getPacketId());
				
				if (networkNodes != null) {					
					for (Iterator<NetworkNode> iterator = networkNodes.iterator(); iterator.hasNext();) {
						NetworkNode networkNode = (NetworkNode) iterator.next();
						networkNode.receive(this, ((ResponseRequest) storedPacket).getPacket());
					}
				}
			}
			
			Thread.yield();
		}
	}

	@Override
	public void lookup(NetworkNode requester, InterestPacket packet) {
		this.requests.add(new LookupRequest(requester, packet));
	}

	@Override
	public void receive(NetworkNode sender, DataPacket packet) {
		this.requests.add(new ResponseRequest(sender, packet));
	}
}
