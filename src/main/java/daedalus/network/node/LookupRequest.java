package daedalus.network.node;

import daedalus.network.protocol.InterestPacket;
import daedalus.network.protocol.Packet;

class LookupRequest extends Request {
	private InterestPacket packet; 
	
	public LookupRequest(NetworkNode sender, InterestPacket packet) {
		super(sender);
		this.packet = packet;
	}

	@Override
	public Packet getPacket() {
		return this.packet;
	}
}
