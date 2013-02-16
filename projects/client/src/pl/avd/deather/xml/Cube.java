package pl.avd.deather.xml;

import javax.xml.bind.annotation.XmlType;

@XmlType
public class Cube {
  private Location location;
  private Rotation rotation;
  private float size;
  private String color;

  public Location getLocation() {
    return location;
  }

  public void setLocation(Location location) {
    this.location = location;
  }

  public float getSize() {
    return size;
  }

  public void setSize(float size) {
    this.size = size;
  }

  public String getColor() {
    return color;
  }

  public void setColor(String color) {
    this.color = color;
  }

  public Rotation getRotation() {
    return rotation;
  }

  public void setRotation(Rotation rotation) {
    this.rotation = rotation;
  }
}
