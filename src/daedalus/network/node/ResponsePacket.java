package daedalus.network.node;

import daedalus.network.protocol.DataPacket;

class ResponsePacket extends Packet {
	private DataPacket packet; 
	
	public ResponsePacket(NetworkNode sender, DataPacket packet) {
		super(sender);
		this.packet = packet;
	}

	public DataPacket getPacket() {
		return packet;
	}

	public void setPacket(DataPacket packet) {
		this.packet = packet;
	}
}
