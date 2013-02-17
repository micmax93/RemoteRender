package pl.avd.deather.object;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;
import pl.avd.deather.xml.Location;
import pl.avd.deather.xml.Rotation;

public class Sphere extends BaseObject {

  private double radius;

  public Sphere(Vector3<Double> position, Vector4<Double> rotation, String color, double radius) {
    super(position, rotation, color);
    this.radius = radius;
  }

  public double getRadius() {
    return radius;
  }

  @Override
  public String info() {
    return "Sphere with radius: " + radius;
  }

  @Override
  public String getBaseName() {
    return "Sphere " + radius;
  }

  @Override
  public Object toXmlObject() {
    pl.avd.deather.xml.Sphere sphere = new pl.avd.deather.xml.Sphere();
    sphere.setRadius((float) radius);
    sphere.setColor(color);
    sphere.setLocation(new Location(
        getPosition().getX().floatValue(),
        getPosition().getY().floatValue(),
        getPosition().getZ().floatValue()
    ));
    sphere.setRotation(new Rotation(
        getRotation().getX().floatValue(),
        getRotation().getY().floatValue(),
        getRotation().getZ().floatValue(),
        getRotation().getW().floatValue()
    ));
    return sphere;
  }
}
