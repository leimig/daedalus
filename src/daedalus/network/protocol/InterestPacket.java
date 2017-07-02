package daedalus.network.protocol;

public class InterestPacket {
	private String dataName;
	
	public InterestPacket(String dataName) {
		this.dataName = dataName;
	}
	
	public String getDataName() {
		return this.dataName;
	}
}
