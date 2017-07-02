package daedalus.network.node;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import daedalus.network.protocol.DataPacket;
import daedalus.network.protocol.InterestPacket;

public class RunnableNetworkNode implements NetworkNode, Runnable {

	private List<Packet> requests;
	
	private List<NetworkNode> forwardingNodes;
	
	private Map<String, List<NetworkNode>> pendingInterestTable;
	
	public RunnableNetworkNode(List<NetworkNode> forwardingNodes) {
		this.requests = new LinkedList<>();

		this.forwardingNodes = forwardingNodes;
		this.pendingInterestTable = new HashMap<>();
	}
	
	@Override
	public void run() {
		
	}

	@Override
	public void lookup(NetworkNode requester, InterestPacket packet) {
		this.requests.add(new LookupPacket(requester, packet));
	}

	@Override
	public void receive(NetworkNode sender, DataPacket packet) {
		this.requests.add(new ResponsePacket(sender, packet));
	}
}
