package pl.avd.deather.xml;

import javax.xml.bind.annotation.XmlType;

@XmlType(propOrder = {"width", "height", "quality"})
public class Properties {
  private int width = 256;
  private int height = 256;
  private int quality = 75;

  public int getWidth() {
    return width;
  }

  public void setWidth(int width) {
    this.width = width;
  }

  public int getHeight() {
    return height;
  }

  public void setHeight(int height) {
    this.height = height;
  }

  public int getQuality() {
    return quality;
  }

  public void setQuality(int quality) {
    this.quality = quality;
  }
}
