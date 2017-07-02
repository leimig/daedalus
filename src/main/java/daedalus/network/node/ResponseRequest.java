package daedalus.network.node;

import daedalus.network.protocol.DataPacket;
import daedalus.network.protocol.Packet;

class ResponseRequest extends Request {
	private DataPacket packet; 
	
	public ResponseRequest(NetworkNode sender, DataPacket packet) {
		super(sender);
		this.packet = packet;
	}

	@Override
	public Packet getPacket() {
		return this.packet;
	}
}
