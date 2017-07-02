package daedalus.network.node.cache;

import daedalus.network.protocol.DataPacket;

public interface ContentStore {
	DataPacket lookup(String name);
	
	boolean cache(DataPacket packet);
}
