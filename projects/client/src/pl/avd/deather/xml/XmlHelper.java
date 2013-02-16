package pl.avd.deather.xml;


import pl.avd.deather.math.Vector3;
import pl.avd.deather.object.BaseObject;
import pl.avd.deather.storage.ObjectStorage;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import java.io.ByteArrayOutputStream;

public class XmlHelper {

  public XmlHelper() {
  }

  public String createXml(Vector3<Float> eye, Vector3<Float> lookAt, ObjectStorage storage, int width, int height, int quality) {
    try {
      Scene scene = createScene(eye, lookAt, storage, width, height, quality);
      ByteArrayOutputStream baos = new ByteArrayOutputStream();

      JAXBContext ctx = JAXBContext.newInstance(Scene.class);
      Marshaller marshaller = ctx.createMarshaller();
      marshaller.marshal(scene, baos);

      String xml = baos.toString();
      return xml;
    } catch (JAXBException e) {
      e.printStackTrace();
    }

    return null;
  }

  private Scene createScene(Vector3<Float> eye, Vector3<Float> lookAt, ObjectStorage storage, int width, int height, int quality) {
    Scene scene = new Scene();
    scene.getCamera().setEye(new Location(eye.x, eye.y, eye.z));
    scene.getCamera().setLookAt(new Location(lookAt.x, lookAt.y, lookAt.z));
    for (BaseObject object : storage.getObjects()) {
      scene.getObjects().getObjects().add(object.toXmlObject());
    }

    scene.getProperties().setHeight(height);
    scene.getProperties().setWidth(width);
    scene.getProperties().setQuality(quality);
    return scene;
  }
}
