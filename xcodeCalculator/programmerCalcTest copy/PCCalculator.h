//
//  PCCalculator.h
//  programmerCalc
//
//  Created by Stephen Long on 17/10/2013.
//  Copyright (c) 2013 Stephen. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PCCalculator : NSObject
@property (retain) NSMutableString *binaryDisplay;
@property (retain) NSMutableString *decimalDisplay;
@property (retain) NSMutableString *hexDisplay;
@property (retain) NSMutableString *octalDisplay;
@property (retain) NSString *base;

-(void) input:(NSString *) character;
-(NSString *) decimalDisplayValue;
-(NSString *) octalDisplayValue;
-(NSString *) binaryDisplayValue;
-(NSString *) hexDisplayValue;

//Converting from Decimal
-(NSString *)decimalToHex:(NSString *)decimalIn;
-(NSString *)decimalToOctal:(NSString *)decimalIn;
-(NSMutableString *)decimalToBinary:(NSString *)decimalIn;

//Converting from Hex
-(NSString *)hexToDecimal:(NSString *)hexIn;
-(NSString *)hexToOctal:(NSString *)hexIn;

//Converting from Octal
-(NSString *)octalToDecimal:(NSString *)octIn;
-(NSString *)octalToHex:(NSString *)octIn;

//Converting from Binary
-(NSString *)binaryToDecimal:(NSString *)binaryIn;
-(NSString *)binaryToHex:(NSString *)binaryIn;
-(NSString *)binaryToOctal:(NSString *)binaryIn;

-(void) deleteEveryThing: (NSString *) character;
-(void)setBaseTo:(NSString *)newBase;

@end
