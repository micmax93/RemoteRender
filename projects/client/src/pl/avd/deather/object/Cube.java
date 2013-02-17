package pl.avd.deather.object;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;
import pl.avd.deather.xml.Location;
import pl.avd.deather.xml.Rotation;

public class Cube extends BaseObject {
  protected double edge;


  public Cube(Vector3<Double> position, Vector4<Double> rotation, String color, double edge) {
    super(position, rotation, color);
    this.edge = edge;
  }

  public double getEdge() {
    return edge;
  }

  @Override
  public String info() {
    return "Cube with edge: " + edge;
  }

  @Override
  public String getBaseName() {
    return "Cube " + edge;
  }

  @Override
  public Object toXmlObject() {
    pl.avd.deather.xml.Cube cube = new pl.avd.deather.xml.Cube();
    cube.setSize((float) edge);
    cube.setColor(color);
    cube.setLocation(new Location(
        getPosition().getX().floatValue(),
        getPosition().getY().floatValue(),
        getPosition().getZ().floatValue()
    ));
    cube.setRotation(new Rotation(
        getRotation().getX().floatValue(),
        getRotation().getY().floatValue(),
        getRotation().getZ().floatValue(),
        getRotation().getW().floatValue()
    ));
    return cube;
  }
}
