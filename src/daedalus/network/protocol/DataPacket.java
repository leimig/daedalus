package daedalus.network.protocol;

public class DataPacket implements Packet {
	private String name;
	
	public DataPacket(String name) {
		this.name = name;
	}
	
	public String getIdentifier() {
		return this.name;
	}
}
