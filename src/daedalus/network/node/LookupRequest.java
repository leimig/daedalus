package daedalus.network.node;

import daedalus.network.protocol.InterestPacket;

class LookupRequest extends Request {
	private InterestPacket packet; 
	
	public LookupRequest(NetworkNode sender, InterestPacket packet) {
		super(sender);
		this.packet = packet;
	}

	public InterestPacket getPacket() {
		return packet;
	}

	public void setPacket(InterestPacket packet) {
		this.packet = packet;
	}
	
	@Override
	public String getPacketId() {
		return this.packet.getDataName();
	}
}
