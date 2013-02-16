package pl.avd.deather.xml;


import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import java.util.List;

public class XmlTest {
  public static void main(String[] args) {
    Scene scene = new Scene();
    List<Object> objects = scene.getObjects().getObjects();

    Cube cube = new Cube();
    cube.setLocation(new Location(1, 2, 3));
    cube.setColor("blue");
    cube.setSize(2.13f);
    objects.add(cube);

    Sphere sphere = new Sphere();
    sphere.setLocation(new Location(4, 5, 6));
    sphere.setColor("red");
    sphere.setRadius(0.2f);
    objects.add(sphere);

    try {
      JAXBContext ctx = JAXBContext.newInstance(Scene.class);
      Marshaller marshaller = ctx.createMarshaller();
      marshaller.marshal(scene, System.out);
    } catch (JAXBException e) {
      e.printStackTrace();
    }
  }
}
