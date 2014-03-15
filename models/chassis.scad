//cylinder(h = 3, r1 = 120, r2 = 120, center = true);

module caster_mask() {
  rotate([0,0,0]) union() {
    translate([   0, 0, -5]) cylinder(h = 10, r = 8.5, center = true, $fs = 0.01);
    translate([ 7.5, 0, -5]) cylinder(h = 10, r = 3.5, center = true, $fs = 0.01);
    translate([-7.5, 0, -5]) cylinder(h = 10, r = 3.5, center = true, $fs = 0.01);
    translate([ 7.5, 0,  5]) cylinder(h = 10, r = 1.2, center = true, $fs = 0.01);
    translate([-7.5, 0,  5]) cylinder(h = 10, r = 1.2, center = true, $fs = 0.01);
    #translate([ 6.5, 0,  5]) cylinder(h = 10, r = 1.2, center = true, $fs = 0.01);
    #translate([-6.5, 0,  5]) cylinder(h = 10, r = 1.2, center = true, $fs = 0.01);
    #translate([7, 0,  5]) cube([1.25, 2.4, 10], center = true);
    #translate([-7, 0,  5]) cube([1.25, 2.4, 10], center = true);
  }
}

module motor_mask() {
  union(){
    translate([0, 0, 5.5]) cube([35,12.5,11], center = true);
    translate([13, -25, -15.6]) cube([15,50,50]);
    translate([0, 10, 0]) cylinder(h = 22.5, r = 1.65, center = true, $fs = 0.01);
    translate([0, -10, 0]) cylinder(h = 22.5, r = 1.65, center = true, $fs = 0.01);
  }
}

module battery() {
  union() {
    cube([76, 40, 2], center = true);
    translate([-38, -20, 0]) cube([76, 2, 15]);
    translate([-38, 18, 0]) cube([76, 2, 15]);
    translate([-38, -13, 0]) cube([2, 26, 15]);
    translate([36, -20, 0]) cube([2, 40, 15]);
    translate([-15, -18, 0]) cube([30, 4, 6]);
    translate([-15, 14, 0]) cube([30, 4, 6]);
    translate([-36, -13, 0]) cube([4, 26, 6]);
    translate([32, -20, 0]) cube([4, 40, 6]);
  }
}

module rover() {
  difference() {
    union() {
      translate([0, 0, 1]) cylinder(h = 1.5, r = 60, center = true, $fn=100);
      translate([0, 40,1.25]) battery();
    }
    #translate([0,  45, -0.01]) caster_mask();
    #translate([0, -30,-0.01]) caster_mask();
    #translate([-35, 0, 2.01]) rotate([0, 0, 180]) motor_mask();
    #translate([ 35, 0, 2.01]) motor_mask();
    #translate([ 45,  30, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([ 45, -25, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([-45,  30, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([-45, -25, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 0]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 20]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -20]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 40]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -40]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 55]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -55]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 130]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -130]) translate([0, -58, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);


    #rotate([0, 0, 0]) translate([0, -52, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 20]) translate([0, -52, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -20]) translate([0, -52, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, 40]) translate([0, -52, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
    #rotate([0, 0, -40]) translate([0, -52, 0]) cylinder(h = 20, r = 1.6, center = true, $fs = 0.01);
  }
}

module top_prototype() {
	difference() {
    union() {
      translate([0, 0, 1]) cylinder(h = 2, r = 60, center = true, $fn=100);
		difference() {
			translate([0, 0, 5]) cube([84, 119.5, 10], center = true);
			translate([0, 0, 7.002]) cube([82, 117.5, 10], center = true);
			translate([28,-60,2.001]) cube([5, 2, 10]);
			translate([-33,-60,2.001]) cube([5, 2, 10]);
			translate([-42.1,42.75,2.001]) cube([2, 5, 10]);
			translate([-42.1,-42.75,2.001]) cube([2, 5, 10]);
		}
    }
    #translate([ 45,  30, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([ 45, -25, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([-45,  30, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);
    #translate([-45, -25, 20]) cylinder(h = 50, r = 1.6, center = true, $fs = 0.01);

    #translate([20, -48.47, 20]) cylinder(h = 50, r = 1.1, center = true, $fs = 0.01);
    #translate([-20, -48.47, 20]) cylinder(h = 50, r = 1.1, center = true, $fs = 0.01);
    #translate([20, 28.25, 20]) cylinder(h = 50, r = 1.1, center = true, $fs = 0.01);
    #translate([-20, 28.25, 20]) cylinder(h = 50, r = 1.1, center = true, $fs = 0.01);
	}
}

translate([0, -80, 0]) rover();
translate([0, 80, 0]) top_prototype();