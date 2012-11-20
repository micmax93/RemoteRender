package pl.avd.deather.storage;

import pl.avd.deather.object.BaseObject;

import java.util.LinkedList;
import java.util.List;

public class ObjectStorage {
  private List<BaseObject> objects = new LinkedList<BaseObject>();

  public ObjectStorage() {
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
