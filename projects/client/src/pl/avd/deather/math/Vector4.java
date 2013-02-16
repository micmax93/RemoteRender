package pl.avd.deather.math;

public class Vector4<T> {
  public T x, y, z, w;

  public Vector4(T x, T y, T z, T w) {
    this.x = x;
    this.y = y;
    this.z = z;
    this.w = w;
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

  public T getW() {
    return w;
  }

  public void setW(T w) {
    this.w = w;
  }

  @Override
  public String toString() {
    return "(" +
        x + ", " +
        y + ", " +
        z + ", " +
        w + ")";
  }
}
