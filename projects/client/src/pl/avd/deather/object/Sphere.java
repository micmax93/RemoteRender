package pl.avd.deather.object;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;

public class Sphere extends BaseObject {

  private double radius;

  public Sphere(Vector3<Double> position, Vector4<Double> rotation, Vector3<Integer> color, double radius) {
    super(position, rotation, color);
    this.radius = radius;
  }

  public double getRadius() {
    return radius;
  }

  @Override
  public String info() {
    return "Sphere with radius: "+radius;
  }
}
