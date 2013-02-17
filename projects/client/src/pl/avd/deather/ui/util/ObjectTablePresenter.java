package pl.avd.deather.ui.util;

import pl.avd.deather.object.BaseObject;

public class ObjectTablePresenter {
  public String[] object2row(BaseObject o) {
    String[] tmp = new String[]{
        o.getBaseName(),
        o.getPosition().toString(),
        o.getRotation().toString(),
//        o.getColor()
    };

    return tmp;
  }
}
