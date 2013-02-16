package pl.avd.deather.math;

public class Vector3<T> {
  public T x;
  public T y;
  public T z;

  public Vector3(T x, T y, T z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  public T getX() {
    return x;
  }

  public void setX(T x) {
    this.x = x;
  }

  public T getY() {
    return y;
  }

  public void setY(T y) {
    this.y = y;
  }

  public T getZ() {
    return z;
  }

  public void setZ(T z) {
    this.z = z;
  }

  @Override
  public String toString() {
    return "(" +
        x + ", " +
        y + ", " +
        z + ")";
  }
}
