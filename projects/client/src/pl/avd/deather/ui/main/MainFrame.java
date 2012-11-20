package pl.avd.deather.ui.main;

import pl.avd.deather.object.BaseObject;
import pl.avd.deather.ui.handler.MenuClickHandler;
import pl.avd.deather.ui.handler.ObjectRemoveHandler;
import pl.avd.deather.ui.util.ObjectTablePresenter;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.List;

public class MainFrame extends JFrame implements MouseListener {
  private JPanel panel1;
  private JTable table;
  private JButton infoButton;
  private JButton removeButton;
  private JButton newButton;
  private JMenuItem cubeMenuItem;
  private JMenuItem sphereMenuItem;
  private JPopupMenu popupMeshSelect;

  private MenuClickHandler clickHandler;
  private ObjectRemoveHandler removeHandler;
  private ObjectTablePresenter presenter;

  public MainFrame(String title, MenuClickHandler handler) {
    this.clickHandler = handler;
    this.presenter = new ObjectTablePresenter();

    setTitle(title);
    setContentPane(panel1);
    panel1.setPreferredSize(new Dimension(800, 600));
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
    table = new JTable(new DefaultTableModel(new Object[]{"Type", "Position", "Rotation", "Color"}, 8));
    table.setSelectionMode(0);
    DefaultTableModel model = (DefaultTableModel) table.getModel();
    //model.addRow(new Object[]{"q", "w", "e", "r\nt"});
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

  public void drawObjects(List<BaseObject> objects) {
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
}
