package pl.avd.deather.xml;

import javax.xml.bind.annotation.XmlType;

@XmlType
public class Sphere {

  private Location location;
  private Rotation rotation;
  private float radius;
  private String color;

  public Location getLocation() {
    return location;
  }

  public void setLocation(Location location) {
    this.location = location;
  }

  public float getRadius() {
    return radius;
  }

  public void setRadius(float radius) {
    this.radius = radius;
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

