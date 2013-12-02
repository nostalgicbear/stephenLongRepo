//
//  PCViewController.m
//  programmerCalc
//
//  Created by Stephen Long on 17/10/2013.
//  Copyright (c) 2013 Stephen. All rights reserved.
//

#import "PCViewController.h"

@interface PCViewController ()

@end

@implementation PCViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    counter = 0;
    [_countLabel setAlpha:0.0];
    
    [_headerLabel setFont:[UIFont fontWithName:@"Digital tech" size:30]];
    for(id label in _baseLabels){
        [label setFont:[UIFont fontWithName:@"Digital tech" size:22]];
    }
    UIFont *font = [UIFont fontWithName:@"Digital tech" size:20];
    NSDictionary *attributes = [NSDictionary dictionaryWithObject:font
                                                           forKey:UITextAttributeFont];
    [_segmentedControl setTitleTextAttributes:attributes
                                    forState:UIControlStateNormal];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//Secret message
-(IBAction)increaseCount:(id)sender{
    counter = counter + 1;
    if(counter ==5){
    _countLabel.text = @"Please give me 80% +";
        [_countLabel setAlpha:1];
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:5.0];
        [_countLabel setAlpha:0.0f];
        [UIView commitAnimations];
    }
}

- (IBAction)playSound:(id)sender{
    SystemSoundID soundID;
    NSString *buttonName = [sender currentTitle];
    NSString *soundFile = [[NSBundle mainBundle]pathForResource:buttonName ofType:@"wav"];
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:soundFile], &soundID);
    AudioServicesPlaySystemSound(soundID);
}


- (IBAction)press:(id)sender {
    [calculator setBaseTo:[NSMutableString stringWithString:[self getSelectedIndex]]];
    [calculator input:[sender titleForState:UIControlStateNormal]];
    [_decimalDisplayField setText:[calculator decimalDisplayValue]];
    [_octalDisplayField setText:[calculator octalDisplayValue]];
    [_binaryDisplayField setText:[calculator binaryDisplayValue]];
    [_hexDisplayField setText:[calculator hexDisplayValue]];
}

-(NSString *)getSelectedIndex{
    if(_segmentedControl.selectedSegmentIndex==0){
        return @"decimal";
    }
    else if(_segmentedControl.selectedSegmentIndex ==1){
        return @"binary";
    }
    else if(_segmentedControl.selectedSegmentIndex==2){
        return @"hexadecimal";
    }
    else if(_segmentedControl.selectedSegmentIndex==3){
        return @"octal";
    }
    else{
        return @"Something went wrong";
    }
}

-(IBAction)segmentControl:(id)sender{
    
    //DECIMAL SELECTED
    if(_segmentedControl.selectedSegmentIndex == 0){
      
        for(id button in _hexButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _binaryButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _octalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        //ENABLE DECIMAL
        for(id button in _decimalButtons){
            [button setEnabled:YES];
            [button setAlpha:1];
        }
    
        for(id fields in _allTextFields){
            [fields setBackgroundColor:[UIColor lightGrayColor]];
        }
        
        [_decimalDisplayField setBackgroundColor:[UIColor greenColor]];
        [_headerLabel setText:@"Decimal Number Base Selected"];
        [_headerLabel setAlpha:1];
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:5.0];
        [_headerLabel setAlpha:0.0f];
        [UIView commitAnimations];
        
    }
    if(_segmentedControl.selectedSegmentIndex ==1){ //BINARY SELECTED
        //disable hex
        for(id button in _hexButtons){
            [button setAlpha:0.2];
            [button setEnabled:NO];
        }
        
        //DISABLE DECIMAL
        for(id button in _decimalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        //disable octal
        for(id button in _octalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        //ENABLE BINARY
        for(id button in _binaryButtons){
            [button setEnabled:YES];
            [button setAlpha:1];
        }
        
        [_headerLabel setText:@"Binary Number Base Selected"];
        [_headerLabel setAlpha:1];
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:5.0];
        [_headerLabel setAlpha:0.0f];
        [UIView commitAnimations];
        
        for(id fields in _allTextFields){
            [fields setBackgroundColor:[UIColor lightGrayColor]];
        }
        [_binaryDisplayField setBackgroundColor:[UIColor greenColor]];
        
    }
    if(_segmentedControl.selectedSegmentIndex == 2){ //HEX SELECTED
        
        //DISABLE DECIMAL
        for(id button in _decimalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _binaryButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _octalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        //ENABLE HEX
        for(id button in _hexButtons){
            [button setEnabled:YES];
            [button setAlpha:1];
        }
        
        [_headerLabel setText:@"Hex Number Base Selected"];
        [_headerLabel setAlpha:1];
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:5.0];
        [_headerLabel setAlpha:0.0f];
        [UIView commitAnimations];
        
        for(id fields in _allTextFields){
            [fields setBackgroundColor:[UIColor lightGrayColor]];
        }
        
        [_hexDisplayField setBackgroundColor:[UIColor greenColor]];

    }
    
    if(_segmentedControl.selectedSegmentIndex == 3){ //OCTAL SELECTED
        
        for(id button in _hexButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _decimalButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _binaryButtons){
            [button setEnabled:NO];
            [button setAlpha:0.2];
        }
        
        for(id button in _octalButtons){
            [button setEnabled:YES];
            [button setAlpha:1];
        }
        
        for(id fields in _allTextFields){
            [fields setBackgroundColor:[UIColor lightGrayColor]];
        }
        
        [_headerLabel setText:@"Octal Number Base Selected"];
        [_headerLabel setAlpha:1];
        [UIView beginAnimations:nil context:NULL];
        [UIView setAnimationDuration:5.0];
        [_headerLabel setAlpha:0.0f];
        [UIView commitAnimations];
        [_octalDisplayField setBackgroundColor:[UIColor greenColor]];
    }
}

-(id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    calculator = [[PCCalculator alloc]init];
    return self;
}

-(IBAction)deleteAllFields:(id)sender{
    [calculator deleteEveryThing:[sender titleForState:UIControlStateNormal]];
    [_decimalDisplayField setText:[calculator decimalDisplayValue]];
    [_octalDisplayField setText:[calculator octalDisplayValue]];
    [_binaryDisplayField setText:[calculator binaryDisplayValue]];
    [_hexDisplayField setText:[calculator hexDisplayValue]];
    
}

- (void)dealloc {
    [_decimalDisplayField release];
    [_hexDisplayField release];
    [_hexButtons release];
    [_binaryButtons release];
    [_decimalButtons release];
    [_octalButtons release];
    [_binaryDisplayField release];
    [_octalDisplayField release];
    [_allTextFields release];
    [_headerLabel release];
    [_deleteButton release];
    [_baseLabels release];
    [super dealloc];
}

@end
