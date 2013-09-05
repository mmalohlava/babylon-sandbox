/* $Id$ */
package cz.cuni.mff.java.reflect;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.table.*;

public class SIntrospector {

  private static void createAndShowGUI() {
    final JFrame frame = new JFrame("Introspector");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    Container pane = frame.getContentPane();
   
    final IntroTableModel model = new IntroTableModel();
    pane.add(new JScrollPane(new JTable(model)));

    JTextField field = new JTextField();
    field.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent ev) {
        String className = ev.getActionCommand();
        try {
          Class<?> clazz = Class.forName(className);
          model.setClassToIntrospect(clazz);
        } catch (Exception ex) {
          JOptionPane.showMessageDialog(frame, "Class " + className + " cannot be loaded!", "Exception", JOptionPane.ERROR_MESSAGE);
        }
      }
    });
    JToolBar bar = new JToolBar();
    bar.add(field);
    field.setToolTipText("Input a class name");

    pane.add(bar, BorderLayout.NORTH);

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

  private static class IntroTableModel extends AbstractTableModel {
    private Class<?> clazz = this.getClass();

    public void setClassToIntrospect(Class<?> clazz) {
      this.clazz = clazz;
      fireTableDataChanged();
    }

    public int getRowCount() {
      return 8;
    }

    public int getColumnCount() {
      return 3;
    }
    
    public String getColumnName(int column) {
      return column == 0 ? "Element" : "Value";
    }

    public Object getValueAt(int row, int column) {
      switch (row) {
        case 0:
          return column == 0 ? "Name" : clazz.getName();
        case 1:
          return column == 0 ? "isPrimitve" : Boolean.toString(clazz.isPrimitive());
        case 2:
          return column == 0 ? "isArray" : Boolean.toString(clazz.isArray());
        case 3:
          return column == 0 ? "isInterface" : Boolean.toString(clazz.isInterface());
        case 4:
          return column == 0 ? "Package" : clazz.getPackage();
        case 5:
          return column == 0 ? "Superclass" : clazz.getSuperclass();
        case 6:
          return column == 0 ? "isEnum" : Boolean.toString(clazz.isEnum());
        case 7:
          return column == 0 ? "isAnnotation" : Boolean.toString(clazz.isAnnotation());
      }
      return null;
    }
  }
}


