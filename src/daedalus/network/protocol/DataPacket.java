package daedalus.network.protocol;

public class DataPacket {
	private String name;
	
	public DataPacket(String name) {
		this.name = name;
	}
	
	public String getName() {
		return this.name;
	}
}
