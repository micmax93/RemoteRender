package pl.avd.deather.ui.dialog;


import pl.avd.deather.ui.handler.SphereDialogOkHandler;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SphereDialog extends JDialog {
  private JButton buttonOK;
  private JButton buttonCancel;
  private JPanel mainPanel;
  private JTextField angleRot;
  private JTextField xRot;
  private JTextField yRot;
  private JTextField zRot;
  private JTextField xPos;
  private JTextField yPos;
  private JTextField zPos;
  private JTextField radius;
  private JComboBox colorComboBox;
  private SphereDialogOkHandler handler;

  private Dimension dim = new Dimension(250, 300);
  private Dimension subDim = new Dimension(250, 40);

  public SphereDialog(SphereDialogOkHandler handler) {
    createWidgets();

    this.handler = handler;

    setMinimumSize(dim);
    setMaximumSize(dim);

    setContentPane(mainPanel);
    setModal(true);
    getRootPane().setDefaultButton(buttonOK);
    setTitle("Create sphere");

// call onCancel() when cross is clicked
    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
        onCancel();
      }
    });

// call onCancel() on ESCAPE
    mainPanel.registerKeyboardAction(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        onCancel();
      }
    }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    pack();
  }

  private void createWidgets() {
    mainPanel = new JPanel();
    mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

    JPanel cubePanel = new JPanel();
    cubePanel.setBorder(BorderFactory.createTitledBorder("Sphere radius and color"));
    cubePanel.setLayout(new BoxLayout(cubePanel, BoxLayout.X_AXIS));
    radius = new JTextField("0.25");
    colorComboBox = new JComboBox(new String[]{"red", "blue"});
    cubePanel.add(radius);
//    cubePanel.add(colorComboBox);
    mainPanel.add(cubePanel);
    cubePanel.setMaximumSize(subDim);

    mainPanel.add(new Box.Filler(subDim, subDim, subDim));

    JPanel positionPanel = new JPanel();
    positionPanel.setBorder(BorderFactory.createTitledBorder("Position"));
    positionPanel.setLayout(new BoxLayout(positionPanel, BoxLayout.X_AXIS));
    xPos = new JTextField("0.0");
    yPos = new JTextField("0.0");
    zPos = new JTextField("0.0");
    positionPanel.add(xPos);
    positionPanel.add(yPos);
    positionPanel.add(zPos);
    mainPanel.add(positionPanel);
    positionPanel.setMaximumSize(subDim);

    mainPanel.add(new Box.Filler(subDim, subDim, subDim));

    JPanel rotationPanel = new JPanel();
    rotationPanel.setBorder(BorderFactory.createTitledBorder("Rotation XYZ alpha"));
    rotationPanel.setLayout(new BoxLayout(rotationPanel, BoxLayout.X_AXIS));
    xRot = new JTextField("0.0");
    yRot = new JTextField("0.0");
    zRot = new JTextField("0.0");
    angleRot = new JTextField("30.0");
    rotationPanel.add(xRot);
    rotationPanel.add(yRot);
    rotationPanel.add(zRot);
    rotationPanel.add(angleRot);
    mainPanel.add(rotationPanel);
    rotationPanel.setMaximumSize(subDim);

    mainPanel.add(new Box.Filler(subDim, subDim, subDim));

    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
    buttonOK = new JButton("OK");
    buttonCancel = new JButton("Cancel");
    buttonPanel.add(buttonOK);
    buttonPanel.add(buttonCancel);
    mainPanel.add(buttonPanel);
    buttonPanel.setMaximumSize(subDim);

    mainPanel.add(new Box.Filler(subDim, subDim, subDim));

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
  }

  private void onOK() {
    try {
      if (Double.valueOf(radius.getText()) <= 0) {
        throw new Exception();
      }

      Validator.checkOrThrow(new JTextField[]{xPos, yPos, zPos, xRot, yRot, zRot, angleRot, radius});

      handler.onOk(Double.parseDouble(xPos.getText()), Double.valueOf(yPos.getText()), Double.valueOf(zPos.getText()),
          Double.valueOf(xRot.getText()), Double.valueOf(yRot.getText()), Double.valueOf(zRot.getText()), Double.valueOf(angleRot.getText()),
          (String) colorComboBox.getSelectedItem(), Double.valueOf(radius.getText()));
      dispose();
    } catch (Exception e) {
      JOptionPane.showMessageDialog(null, "Must be valid floating point number.\nRadius must be > 0.", "Error", JOptionPane.ERROR_MESSAGE);
    }
  }


  private void onCancel() {
// add your code here if necessary
    dispose();
  }

}
