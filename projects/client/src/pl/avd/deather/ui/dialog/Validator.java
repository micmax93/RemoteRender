package pl.avd.deather.ui.dialog;


import javax.swing.*;

public class Validator {
  public static void checkOrThrow(JTextField elems[]) throws Exception {
    for (JTextField elem : elems) {
      if (!elem.getText().matches("^-?(?:\\d+|\\d*\\.\\d+)$")) {
        throw new Exception();
      }
    }
  }
}


