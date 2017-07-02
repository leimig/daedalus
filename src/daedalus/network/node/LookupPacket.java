package daedalus.network.node;

import daedalus.network.protocol.InterestPacket;

class LookupPacket extends Packet {
	private InterestPacket packet; 
	
	public LookupPacket(NetworkNode sender, InterestPacket packet) {
		super(sender);
		this.packet = packet;
	}

	public InterestPacket getPacket() {
		return packet;
	}

	public void setPacket(InterestPacket packet) {
		this.packet = packet;
	}
}
