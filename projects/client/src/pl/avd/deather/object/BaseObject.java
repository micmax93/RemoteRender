package pl.avd.deather.object;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;

public abstract class BaseObject {
  protected Vector3<Double> position;
  protected Vector4<Double> rotation;
  protected String color;

  public BaseObject(Vector3<Double> position, Vector4<Double> rotation, String color) {
    this.position = position;
    this.rotation = rotation;
    this.color = color;
  }

  public Vector3<Double> getPosition() {
    return position;
  }

  public Vector4<Double> getRotation() {
    return rotation;
  }

  public String getColor() {
    return color;
  }

  public abstract String info();

  public abstract String getBaseName();

  public abstract Object toXmlObject();
}
