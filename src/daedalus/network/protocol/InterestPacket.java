package daedalus.network.protocol;

public class InterestPacket implements Packet {
	private String dataName;
	
	public InterestPacket(String dataName) {
		this.dataName = dataName;
	}
	
	public String getIdentifier() {
		return this.dataName;
	}
}
