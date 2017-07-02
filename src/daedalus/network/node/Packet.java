package daedalus.network.node;

abstract class Packet {
	private NetworkNode sender;
	
	Packet(NetworkNode sender) {
		this.sender = sender;
	}

	public NetworkNode getSender() {
		return sender;
	}

	public void setSender(NetworkNode sender) {
		this.sender = sender;
	}
}
