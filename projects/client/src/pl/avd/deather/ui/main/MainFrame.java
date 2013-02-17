package pl.avd.deather.ui.main;

import pl.avd.deather.math.Vector3;
import pl.avd.deather.object.BaseObject;
import pl.avd.deather.ui.handler.MenuClickHandler;
import pl.avd.deather.ui.handler.ObjectRemoveHandler;
import pl.avd.deather.ui.util.ObjectTablePresenter;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Hashtable;

public class MainFrame extends JFrame implements MouseListener {
  public interface ClickHandler {
    public void onClick();
  }

  JPanel mainPanel;
  JPanel tablePanel;
  JPanel cameraPanel;
  JPanel buttonsPanel;

  JTextField server;
  JTextField port;

  private JTable table;
  private JButton infoButton;
  private JButton removeButton;
  private JButton newButton;
  private JButton drawButton;

  private JMenuItem cubeMenuItem;
  private JMenuItem sphereMenuItem;
  private JPopupMenu popupMeshSelect;
  private MenuClickHandler clickHandler;
  private ObjectRemoveHandler removeHandler;
  private ObjectTablePresenter presenter;

  private JComboBox widthComboBox;
  private JComboBox heightComboBox;
  private JSlider eyeSliderX;
  private JSlider eyeSliderY;
  private JSlider eyeSliderZ;
  private JSlider lookAtSliderX;
  private JSlider lookAtSliderY;
  private JSlider lookAtSliderZ;
  private JSlider qualitySlider;

  public MainFrame(String title, MenuClickHandler handler) {
    this.clickHandler = handler;
    this.presenter = new ObjectTablePresenter();

    createUIComponents();

    setTitle(title);
    setContentPane(mainPanel);

    mainPanel.setPreferredSize(new Dimension(800, 700));
    setMinimumSize(new Dimension(800, 700));
    setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    pack();

    setupNewButton();
    setupRemoveButton();

    setVisible(true);
  }

  private void setupRemoveButton() {
    removeButton.addMouseListener(this);
  }

  private void createUIComponents() {
    createPanels();
    createTable();
    createButtons();
    createCameraWidgets();
  }

  private void createPanels() {
    mainPanel = new JPanel(new BorderLayout(0, 0));

    tablePanel = new JPanel(new BorderLayout());
    mainPanel.add(tablePanel, BorderLayout.CENTER);

    cameraPanel = new JPanel();
    cameraPanel.setLayout(new BoxLayout(cameraPanel, BoxLayout.Y_AXIS));
    cameraPanel.setPreferredSize(new Dimension(250, 0));
    cameraPanel.setBorder(BorderFactory.createEtchedBorder());
    mainPanel.add(cameraPanel, BorderLayout.EAST);

    buttonsPanel = new JPanel();
    buttonsPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
    mainPanel.add(buttonsPanel, BorderLayout.SOUTH);
  }

  private void createButtons() {
    server = new JTextField("127.0.0.1", 16);
    port = new JTextField("33666", 6);

    drawButton = new JButton("Request draw");
    infoButton = new JButton("Show info");
    newButton = new JButton("Create new");
    removeButton = new JButton("Remove");

    buttonsPanel.add(server);
    buttonsPanel.add(port);
    buttonsPanel.add(drawButton);
    buttonsPanel.add(newButton);
    buttonsPanel.add(removeButton);
//    buttonsPanel.add(infoButton);

    addDrawClickHandler(null);
  }

  private void createTable() {
    table = new JTable(new DefaultTableModel(new Object[]{"Object", "Position", "Rotation"}, 0) {
      @Override
      public boolean isCellEditable(int row, int column) {
        return false;
      }
    });
    table.setSelectionMode(0); // single row selection
    JScrollPane scrollPane = new JScrollPane(table);
    tablePanel.add(scrollPane);
  }

  private void createCameraWidgets() {
    Dimension d = new Dimension(0, 10);
    Dimension d2 = new Dimension(0, 5);

    qualitySlider = createCameraSlider("Quality", 500, 1000, 100, 50);
    widthComboBox = new JComboBox(new String[]{"128 x 128", "256 x 256", "512 x 512"});
//    heightComboBox = new JComboBox(new Integer[]{128, 256, 512});

    JPanel sizePanel = new JPanel();
    sizePanel.setLayout(new BoxLayout(sizePanel, BoxLayout.Y_AXIS));
    sizePanel.setBorder(BorderFactory.createTitledBorder("Image width/height"));
    sizePanel.add(widthComboBox);
//    sizePanel.add(new Box.Filler(d2, d2, d2));
//    sizePanel.add(heightComboBox);
    sizePanel.setMaximumSize(new Dimension(250, 50));

    cameraPanel.add(qualitySlider);
    cameraPanel.add(sizePanel);

    eyeSliderX = createCameraSlider("Eye X", -100, 100, 50, 10);
    eyeSliderY = createCameraSlider("Eye Y", -100, 100, 50, 10);
    eyeSliderZ = createCameraSlider("Eye Z", -100, 100, 50, 10);
    lookAtSliderX = createCameraSlider("Look At X", -100, 100, 50, 10);
    lookAtSliderY = createCameraSlider("Look At Y", -100, 100, 50, 10);
    lookAtSliderZ = createCameraSlider("Look At Z", -100, 100, 50, 10);

    eyeSliderX.setValue(-25);
    eyeSliderY.setValue(-25);
    eyeSliderZ.setValue(-25);
    lookAtSliderX.setValue(0);
    lookAtSliderY.setValue(0);
    lookAtSliderZ.setValue(0);

    cameraPanel.add(eyeSliderX);
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(eyeSliderY);
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(eyeSliderZ);
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(lookAtSliderX);
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(lookAtSliderY);
    cameraPanel.add(new Box.Filler(d, d, d));
    cameraPanel.add(lookAtSliderZ);
    cameraPanel.add(new Box.Filler(d, d, d));
  }

  private JSlider createCameraSlider(String title, int min, int max, int major, int minor) {
    JSlider s = new JSlider();
    s.setMinimum(min);
    s.setMaximum(max);
    s.setBorder(BorderFactory.createTitledBorder(title));
    s.setMajorTickSpacing(major);
    s.setMinorTickSpacing(minor);
    s.setPaintTicks(true);
    s.setPaintLabels(true);
    s.setValue((min + max) / 2);

    Hashtable labels = new Hashtable();
    labels.put(min, new JLabel(String.valueOf(min / 10)));
    labels.put(0, new JLabel(String.valueOf((max + min) / 20)));
    labels.put(max, new JLabel(String.valueOf(max / 10)));
    s.setLabelTable(labels);
    return s;
  }

  private void setupNewButton() {
    popupMeshSelect = new JPopupMenu("Choose mesh");
    popupMeshSelect.setLocation(newButton.getLocation());
    cubeMenuItem = new JMenuItem("Cube");
    sphereMenuItem = new JMenuItem("Sphere");
    popupMeshSelect.add(cubeMenuItem);
    popupMeshSelect.add(sphereMenuItem);

    cubeMenuItem.addMouseListener(this);
    sphereMenuItem.addMouseListener(this);
    newButton.addMouseListener(this);
  }


  @Override
  public void mousePressed(MouseEvent e) {
    popupMeshSelect.setVisible(false);
    if (e.getComponent().equals(newButton)) {
      popupMeshSelect.show(e.getComponent(), e.getX(), e.getY());
    } else if (e.getComponent().equals(cubeMenuItem)) {
      clickHandler.onClick("CUBE");
    } else if (e.getComponent().equals(sphereMenuItem)) {
      clickHandler.onClick("SPHERE");
    } else if (e.getComponent().equals(removeButton)) {
      onRemove();
    }
  }

  private void onRemove() {
    int selected = table.getSelectedRow();
    if (selected >= 0) {
      removeHandler.onRemove(selected);
      ((DefaultTableModel) table.getModel()).removeRow(selected);
    }
  }

  public void drawObjects(java.util.List<BaseObject> objects) {
    clearTable();

    DefaultTableModel dtm = (DefaultTableModel) this.table.getModel();
    for (BaseObject o : objects) {
      dtm.addRow(presenter.object2row(o));
    }
  }

  private void clearTable() {
    DefaultTableModel dtm = (DefaultTableModel) this.table.getModel();
    while (dtm.getRowCount() > 0) {
      dtm.removeRow(0);
    }
  }

  @Override
  public void mouseReleased(MouseEvent e) {
  }

  @Override
  public void mouseEntered(MouseEvent e) {
  }

  @Override
  public void mouseExited(MouseEvent e) {
  }

  @Override
  public void mouseClicked(MouseEvent e) {
  }

  public void setRemoveHandler(ObjectRemoveHandler removeHandler) {
    this.removeHandler = removeHandler;
  }

  public void addDrawClickHandler(final ClickHandler handler) {
    drawButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent actionEvent) {
        if (handler != null) {
          handler.onClick();
        }
      }
    });
  }

  public Vector3<Float> getCameraEye() {
    return new Vector3<Float>(
        eyeSliderX.getValue() / 10f,
        eyeSliderY.getValue() / 10f,
        eyeSliderZ.getValue() / 10f
    );
  }

  public Vector3<Float> getCameraLookAt() {
    return new Vector3<Float>(
        lookAtSliderX.getValue() / 10f,
        lookAtSliderY.getValue() / 10f,
        lookAtSliderZ.getValue() / 10f
    );
  }

  public int getImageWidth() {
    String x = (String) widthComboBox.getSelectedItem();
    return Integer.valueOf(x.substring(0, 3));
  }

  public int getImageHeight() {
    String x = (String) widthComboBox.getSelectedItem();
    return Integer.valueOf(x.substring(0, 3));
  }

  public int getQuality() {
    return (int) (qualitySlider.getValue() / 10f);
  }

  public int getPort() {
    return Integer.valueOf(port.getText());
  }

  public String getHost() {
    return server.getText();
  }
}
