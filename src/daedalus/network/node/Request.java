package daedalus.network.node;

abstract class Request {
	private NetworkNode sender;
	
	Request(NetworkNode sender) {
		this.sender = sender;
	}

	public NetworkNode getSender() {
		return sender;
	}

	public void setSender(NetworkNode sender) {
		this.sender = sender;
	}
	
	public abstract String getPacketId();
}
