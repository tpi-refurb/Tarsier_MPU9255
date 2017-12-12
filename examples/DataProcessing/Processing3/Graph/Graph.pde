import processing.serial.*;
Serial serial;

final int width = 1000;
final int height = 600;
final int minAngle = -180;
final int maxAngle = 180;


int [] degrees = new int[]{90, 0, -90};
int axesCount = 9;
float[][] data = new float[width][axesCount];
float[] rawData = new float[axesCount];
String[] labels = new String[]{"Accel X", "Accel Y", "Accel Z", "Gyro X", "Gyro Y", "Gyro Z", "Mag X", "Mag Y", "Mag Z"};
color[] colors = new color[]{ #0734ff, #037f76, #07ffed, #9307ff, #d107ff, #ff076e, #ff5400, #fff202, #05ff00};
float[] strokes = new float[]{ 4, 3, 2, 1.8, 1.6, 1.4, 1.2, 1, 1};

boolean drawValues  = false;
boolean enableVerbose = false;

void setup() {
  //fullScreen();
  size(1000, 600);  
  //size(1000, 600,P3D);
  rectMode(CENTER); 
  surface.setTitle("Data Processing Plotter -Marianz");

  println(Serial.list()); // Use this to print connected serial devices
  //serial = new Serial(this, Serial.list()[0], 115200); // Set this to your serial port obtained using the line above
  serial = new Serial(this, "COM13", 115200); // Set this to your serial port obtained using the line above
  serial.bufferUntil('\n'); // Buffer until line feed

  //Set all data line into default value to a center of height size
  for (int r = 0; r < width; r++) {
    for (int a = 0; a < axesCount; a++) {
      data[r][a] =  height/2;
    }
  }
  drawGraph(); // Draw graph at startup
}

void draw() {
  /* Draw Graph */
  if (drawValues) {
    drawValues = false;
    drawGraph();
    drawMarker();
    drawAxes();
    printLegends();
  }
}

void drawGraph() {
  /* Draw vertical and horizontal gridlines*/
  strokeWeight(1);
  background(0); // Black
  for (int i = 0; i < width; i++) {
    stroke(21, 21, 21); // Dark Grey
    line(i*10, 0, i*10, height);
    line(0, i*10, width, i*10);
  }
}


void printLegends() {
  /* Legends and its values from array data storage */
  textSize(18);  
  for (int i=0; i< labels.length; i++) {
    fill(colors[i]);  
    text(labels[i], 10, 40+(20*i), 0);      
    text(rawData[i], 100, 40+(20*i), 0);
  }
}

void drawMarker() {
  /* draw marker lines to simply indicate current reading value */
  strokeWeight(1);
  textSize(14);
  for (int i = 1; i <= degrees.length; i++) {  
    fill(160, 160, 160);         //Gray
    stroke(166, 128, 166);       //#A680A6
    text(degrees[i-1]+" Degree ", width-100, height/4*i);
    line(0, height/4*i, width, height/4*i); // Draw line, indicating -90 deg, 0 deg and 90 deg
  }
}

void drawAxes() {
  /* And now let's create a graph lines */
  noFill();
  strokeWeight(1);
  stroke(255, 255, 0); // Yellow
  // Redraw everything
  int rows = data.length;
  for (int a = 0; a < axesCount; a++) {
    beginShape();
    vertex(0, data[0][0]);
    strokeWeight(strokes[a]);
    stroke(colors[a]);
    for (int r = 1; r < rows; r++) {
      float newValue = data[r][a];
      float oldValue = data[r-1][a];
      if ((newValue < height/4 && oldValue> height/4*3) || (newValue> height/4*3 && oldValue < height/4)) {      
        endShape();
        beginShape();
      }
      //println("r: "+ r+" a: "+ a+" "+data[r][a]);
      vertex(r, data[r][a]);
    }
    endShape();
  }
  noStroke();

  // Put all data one array back
  for (int a = 0; a < axesCount; a++) {   
    for (int r = 1; r < rows; r++) {   
      data[r-1][a] = data[r][a];
    }
  }
}

void serialEvent (Serial serial) {
  try {
    // Get the ASCII strings:
    String serialData = serial.readStringUntil('\n');
    if (serialData !=null) {
      String []chunks = splitTokens(serialData, "\t");
      if (chunks.length>0) {
        for (int i =0; i<chunks.length; i++) {
          if (chunks[i] != null) {
            float val = float(trim(chunks[i])); // Trim off any whitespace
            data[data.length -1][i] = map(val, minAngle, maxAngle, 0, height); // Convert to a float and map to the screen height, then save in buffer
            rawData[i] = val;
            if (val > height) {
            }
          }
        }
      }
    }
  } 
  catch(Exception e) {
  } 
  finally {
    serial.clear(); // Clear buffer
    drawValues = true; // Draw the graph
  }
}