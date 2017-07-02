package daedalus.network.node.cache.policy;

import daedalus.network.node.cache.ContentStore;
import daedalus.network.protocol.DataPacket;

public class NoCache implements ContentStore {
	@Override
	public DataPacket lookup(String name) {
		return null;
	}

	@Override
	public boolean cache(DataPacket packet) {
		return false;
	}
}
