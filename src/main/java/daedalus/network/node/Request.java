package daedalus.network.node;

import daedalus.network.protocol.Packet;

abstract class Request {
	private NetworkNode sender;
	
	Request(NetworkNode sender) {
		this.sender = sender;
	}

	public NetworkNode getSender() {
		return sender;
	}

	public abstract Packet getPacket();
}
