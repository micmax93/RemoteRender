package pl.avd.deather.ui.dialog;

import pl.avd.deather.ui.handler.CubeDialogOkHandler;

import javax.swing.*;
import java.awt.event.*;

public class CubeDialog extends JDialog {
  private JPanel contentPane;
  private JButton buttonOK;
  private JButton buttonCancel;
  private JSlider edgeSlider;
  private JSlider redSlider;
  private JSlider greenSlider;
  private JSlider blueSlider;
  private JSlider angleSlider;
  private JTextField xRot;
  private JTextField yRot;
  private JTextField zRot;
  private JTextField xPos;
  private JTextField yPos;
  private JTextField zPos;
  private CubeDialogOkHandler handler;

  public CubeDialog(CubeDialogOkHandler handler) {
    this.handler = handler;
    setContentPane(contentPane);
    setModal(true);
    getRootPane().setDefaultButton(buttonOK);
    setTitle("Create new cube");

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
        edgeSlider.getValue());

    dispose();
  }

  private void onCancel() {
// add your code here if necessary
    dispose();
  }

//  public static void main(String[] args) {
//    CubeDialog dialog = new CubeDialog();
//    dialog.pack();
//    dialog.setVisible(true);
//    System.exit(0);
//  }
}
