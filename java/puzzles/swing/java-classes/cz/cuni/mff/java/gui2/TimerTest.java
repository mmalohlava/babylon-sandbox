/* $Id$ */
package cz.cuni.mff.java.gui2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TimerTest implements ActionListener {
  private JPanel panel;
  private JLabel label;
  private JButton button;
  private JProgressBar bar;
  private SwingWorker<String, Object> sw;
  private Timer timer;
  
  private Component createComponents() {
    panel = new JPanel(new GridLayout(0, 1));
    
    panel.setBorder(BorderFactory.createEmptyBorder(30, 30, 10, 30));
    
    button = new JButton("Pocitej");
    button.addActionListener(this);
    panel.add(button);

    bar = new JProgressBar(0, 100);
    panel.add(bar);

    label = new JLabel("Nenastaveno");
    panel.add(label);

    timer = new Timer(100, new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
              bar.setValue(sw.getProgress());
              if (sw.isDone()) {
                timer.stop();
                button.setEnabled(true);
                panel.setCursor(null);
                String ret = null;
                try {
                  ret = sw.get();
                } catch (Exception ex) {}
                label.setText(ret);
                bar.setValue(bar.getMinimum());
              }
            }
    });

    return panel;
  }

  public void actionPerformed(ActionEvent e) {
    label.setText("Pocitam...");
    button.setEnabled(false);
    panel.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
    sw = new SwingWorker<String, Object> (){
      public String doInBackground() {
        for (int i = 0; i < 100; i++) {
          setProgress(i);
          try {
            Thread.sleep(100);
          } catch (Exception ex) {}
        }
        return "Hotovo :-)";
      }
    };
    sw.execute();
    timer.start();
  }

  private static void createAndShowGUI() {
    JFrame frame = new JFrame("TimerTest");

    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    TimerTest ap = new TimerTest();
    Component panel = ap.createComponents();
    
    frame.getContentPane().add(panel);
    
    frame.pack();
    frame.setVisible(true);
  }

  public static void main(String[] args) {
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        createAndShowGUI();
      }
    }); 
  }


}


