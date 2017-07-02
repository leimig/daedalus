package daedalus.network.node;

import daedalus.network.protocol.DataPacket;

class ResponseRequest extends Request {
	private DataPacket packet; 
	
	public ResponseRequest(NetworkNode sender, DataPacket packet) {
		super(sender);
		this.packet = packet;
	}

	public DataPacket getPacket() {
		return packet;
	}

	public void setPacket(DataPacket packet) {
		this.packet = packet;
	}
	
	@Override
	public String getPacketId() {
		return this.packet.getName();
	}
}
