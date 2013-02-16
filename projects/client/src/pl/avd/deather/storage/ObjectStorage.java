package pl.avd.deather.storage;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.math.Vector4;
import pl.avd.deather.object.BaseObject;
import pl.avd.deather.object.Cube;

import java.util.LinkedList;
import java.util.List;

public class ObjectStorage {
  private List<BaseObject> objects = new LinkedList<BaseObject>();

  public ObjectStorage() {
    addSampleObject();
  }

  private void addSampleObject() {
    objects.add(new Cube(new Vector3<Double>(0., 0., 0.), new Vector4<Double>(0., 1., 0., 30.), "red", 0.5));
  }

  public void add(BaseObject o) {
    objects.add(o);
  }

  public List<BaseObject> getObjects() {
    return objects;
  }

  public void remove(int i) {
    objects.remove(i);
  }
}
