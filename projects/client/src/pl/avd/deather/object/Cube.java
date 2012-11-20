package pl.avd.deather.object;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;

public class Cube extends BaseObject {
  protected double edge;


  public Cube(Vector3<Double> position, Vector4<Double> rotation, Vector3<Integer> color, double edge) {
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
}
