package pl.avd.deather.xml;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElements;
import javax.xml.bind.annotation.XmlType;
import java.util.ArrayList;
import java.util.List;

@XmlType
public class Objects {
  private List<Object> objects = new ArrayList<Object>();

  @XmlElements({
      @XmlElement(name = "cube", type = Cube.class),
      @XmlElement(name = "sphere", type = Sphere.class)
  })
  public List<Object> getObjects() {
    return objects;
  }

  public void setObjects(List<Object> objects) {
    this.objects = objects;
  }
}
