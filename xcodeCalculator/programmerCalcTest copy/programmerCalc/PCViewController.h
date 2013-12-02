//
//  PCViewController.h
//  programmerCalc
//
//  Created by Stephen Long on 17/10/2013.
//  Copyright (c) 2013 Stephen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "PCCalculator.h"

int counter;

@interface PCViewController : UIViewController
{
    PCCalculator *calculator;
}

-(NSString *)getSelectedIndex;

//Actions
- (IBAction)press:(id)sender;

-(IBAction)deleteAllFields:(id)sender;

- (IBAction)playSound:(id)sender;

-(IBAction)segmentControl:(id)sender;

-(IBAction)increaseCount:(id)sender;

//Textfield

@property (retain, nonatomic) IBOutlet UITextField *decimalDisplayField;

@property (retain, nonatomic) IBOutlet UITextField *hexDisplayField;

@property (retain, nonatomic) IBOutlet UITextField *binaryDisplayField;

@property (retain, nonatomic) IBOutlet UITextField *octalDisplayField;

//segment control

@property (retain, nonatomic) IBOutlet UISegmentedControl *segmentedControl;

//OUTLET COLLECTIONS

@property (retain, nonatomic) IBOutletCollection(UITextField) NSArray *allTextFields;

@property (retain, nonatomic) IBOutletCollection(UIButton) NSArray *hexButtons;

@property (retain, nonatomic) IBOutletCollection(UIButton) NSArray *binaryButtons;

@property (retain, nonatomic) IBOutletCollection(UIButton) NSArray *decimalButtons;

@property (retain, nonatomic) IBOutletCollection(UIButton) NSArray *octalButtons;

@property (retain, nonatomic) IBOutletCollection(UILabel) NSArray *baseLabels;

//LABELS

@property (retain, nonatomic) IBOutlet UILabel *headerLabel;

@property (retain, nonatomic) IBOutlet UILabel *countLabel;

//Delete button
@property (retain, nonatomic) IBOutlet UIButton *deleteButton;

@end
