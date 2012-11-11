package pl.avd.deather.ui.main;

import pl.avd.deather.event.RequestButtonClickHandler;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class MainForm extends JFrame {
  private JPanel mainPanel;
  private JPanel bottomPanel;
  private JTextField ipInput;
  private JTextField portInput;
  private JButton requestButton;
  private JTextArea textArea;


  public MainForm(String title) {
    setTitle(title);
    setContentPane(mainPanel);
    setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    pack();
    setVisible(true);
  }

  public void setHandler(final RequestButtonClickHandler handler) {
    requestButton.addMouseListener(new MouseListener() {
      @Override
      public void mouseClicked(MouseEvent e) {
        handler.onClick(ipInput.getText(), portInput.getText());
      }

      @Override
      public void mousePressed(MouseEvent e) {
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
    });
  }

  public void setTextAreaContent(String content) {
    this.textArea.setText(content);
  }
}
