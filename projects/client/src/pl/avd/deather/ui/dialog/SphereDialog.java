package pl.avd.deather.ui.dialog;

import pl.avd.deather.ui.handler.SphereDialogOkHandler;

import javax.swing.*;
import java.awt.event.*;

public class SphereDialog extends JDialog {
  private JPanel contentPane;
  private JButton buttonOK;
  private JButton buttonCancel;
  private JTextField xPos;
  private JTextField yPos;
  private JTextField zPos;
  private JSlider angleSlider;
  private JTextField xRot;
  private JTextField yRot;
  private JTextField zRot;
  private JSlider redSlider;
  private JSlider greenSlider;
  private JSlider blueSlider;
  private JSlider radiusSlider;
  private SphereDialogOkHandler handler;

  public SphereDialog(SphereDialogOkHandler handler) {
    this.handler = handler;
    setContentPane(contentPane);
    setModal(true);
    getRootPane().setDefaultButton(buttonOK);
    setTitle("Create new sphere");

    buttonOK.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        onOK();
      }
    });

    buttonCancel.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        onCancel();
      }
    });

// call onCancel() when cross is clicked
    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
        onCancel();
      }
    });

// call onCancel() on ESCAPE
    contentPane.registerKeyboardAction(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        onCancel();
      }
    }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    pack();
  }

  private void onOK() {
    handler.onOk(Double.valueOf(xPos.getText()), Double.valueOf(yPos.getText()), Double.valueOf(zPos.getText()),
        Double.valueOf(xRot.getText()), Double.valueOf(yRot.getText()), Double.valueOf(zRot.getText()), angleSlider.getValue(),
        redSlider.getValue(), greenSlider.getValue(), blueSlider.getValue(),
        radiusSlider.getValue());
    dispose();
  }

  private void onCancel() {
// add your code here if necessary
    dispose();
  }

//  public static void main(String[] args) {
//    SphereDialog dialog = new SphereDialog();
//    dialog.pack();
//    dialog.setVisible(true);
//    System.exit(0);
//  }
}
