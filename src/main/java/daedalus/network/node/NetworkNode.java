package daedalus.network.node;

import daedalus.network.protocol.DataPacket;
import daedalus.network.protocol.InterestPacket;

public interface NetworkNode {
	void lookup(NetworkNode requester, InterestPacket packet);
	
	void receive(NetworkNode sender, DataPacket packet);
}
