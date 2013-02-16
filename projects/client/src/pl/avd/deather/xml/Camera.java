package pl.avd.deather.xml;


import javax.xml.bind.annotation.XmlType;

@XmlType
public class Camera {

  private Location eye = new Location();
  private Location lookAt = new Location();

  public Location getLookAt() {
    return lookAt;
  }

  public void setLookAt(Location lookAt) {
    this.lookAt = lookAt;
  }

  public Location getEye() {
    return eye;
  }

  public void setEye(Location eye) {
    this.eye = eye;
  }
}
