//
//  PCCalculator.m
//  programmerCalc
//
//  Created by Stephen Long on 17/10/2013.
//  Copyright (c) 2013 Stephen. All rights reserved.
//

#import "PCCalculator.h"

const NSString *clear = @"clear";

@implementation PCCalculator

-(id)init{
    if(self = [super init]){
        _binaryDisplay = [[NSMutableString stringWithCapacity:32]retain];
        _decimalDisplay = [[NSMutableString stringWithCapacity:32]retain];
        _octalDisplay = [[NSMutableString stringWithCapacity:32]retain];
        _hexDisplay = [[NSMutableString stringWithCapacity:32]retain];
    }
    return self;
}

-(void) dealloc {
    [_binaryDisplay release];
    [_decimalDisplay release];
    [_octalDisplay release];
    [_hexDisplay release];
    [super dealloc];
}

-(void)setBaseTo:(NSString *)newBase{
    _base = newBase;
}

-(void) input : (NSString *)character{
    if([_base isEqualToString: @"decimal"]){
        [_decimalDisplay appendString:character];
        [_hexDisplay setString:[self decimalToHex:_decimalDisplay]];
        [_octalDisplay setString:[self decimalToOctal:_decimalDisplay]];
        [_binaryDisplay setString:[self decimalToBinary:_decimalDisplay]];
    }
    else if ([_base isEqualToString:@"binary"]) {
        [_binaryDisplay  appendString:character];
        [_decimalDisplay setString:[self binaryToDecimal:_binaryDisplay]];
        [_octalDisplay setString:[self binaryToOctal:_binaryDisplay]];
        [_hexDisplay setString:[self binaryToHex:_binaryDisplay]];
    }
    else if([_base isEqualToString:@"hexadecimal"]){
        [_hexDisplay appendString:character];
        [_decimalDisplay setString:[self hexToDecimal:_hexDisplay]];
        [_octalDisplay setString:[self hexToOctal:_hexDisplay]];
        [_binaryDisplay setString:[self decimalToBinary:[self hexToDecimal:_hexDisplay]]];
    }
    else if([_base isEqualToString:@"octal"]){
        [_octalDisplay appendString:character];
        [_decimalDisplay setString:[self octalToDecimal:_octalDisplay]];
        [_hexDisplay setString:[self octalToHex:_octalDisplay]];
        [_binaryDisplay setString:[self decimalToBinary:[self octalToDecimal:_octalDisplay]]];
    }
}

//CONVERSION METHODS -FROM DECIMAL

-(NSString *)decimalToHex : (NSString *)decimalIn{
    NSString *stephenDec = decimalIn;
    NSString *stephenHex = [NSString stringWithFormat:@"%1x", [stephenDec integerValue]];
    return [[stephenHex copy]autorelease];
}

-(NSString *)decimalToOctal:(NSString *)decimalIn{
    NSString *stephenDec = decimalIn;
    NSString *stephenOct = [NSString stringWithFormat:@"%1o", [stephenDec integerValue]];
    return [[stephenOct copy]autorelease];
}

-(NSMutableString *)decimalToBinary:(NSString *)decimalIn{
    NSInteger decimal = decimalIn.intValue;
    NSMutableString *str = [NSMutableString stringWithString:@""];
    NSInteger numberCopy = decimal;
    
    for(NSInteger i=0; i<31; i++){
        [str insertString:((numberCopy & 1)? @"1":@"0") atIndex:0];
        numberCopy >>= 1;
    }
    return str;
}

//CONVERSION METHODS -FROM HEX
-(NSString *)hexToDecimal:(NSString *)hexIn{
    int hex = 0;
    hex = strtol(hexIn.UTF8String,NULL,16);
    NSString *dec = [NSString stringWithFormat:@"%1d", hex];
    return dec;
}

-(NSString *)hexToOctal:(NSString *)hexIn{
    int decimal =0;
    decimal = strtol(hexIn.UTF8String,NULL,16);
    NSString *stephenOct = [NSString stringWithFormat:@"%1o",decimal];
    return stephenOct;
}

//CONVERSION METHODS -FROM OCTAL
-(NSString *)octalToDecimal:(NSString *)octIn{
    int oct =0;
    oct = strtol(octIn.UTF8String, NULL, 8);
    NSString *dec = [NSString stringWithFormat:@"%1d", oct];
    return dec;
}

-(NSString *)octalToHex:(NSString *)octIn{
    int oct = 0;
    oct = strtol(octIn.UTF8String, NULL, 8);
    NSString *stephenHex = [NSString stringWithFormat:@"%1x",oct];
    return stephenHex;
}

//CONVERSION METHODS -FROM BINARY
-(NSString *)binaryToDecimal:(NSString *)binaryIn{
    int bin = 0;
    bin = strtol(binaryIn.UTF8String,NULL,2);
    NSString *dec = [NSString stringWithFormat:@"%1d", bin];
    return dec;
}

-(NSString *)binaryToHex:(NSString *)binaryIn{
    int bin = 0;
    bin = strtol(binaryIn.UTF8String,NULL,2);
    NSString *hex = [NSString stringWithFormat:@"%1x", bin];
    return hex;
}

-(NSString *)binaryToOctal:(NSString *)binaryIn{
    int bin = 0;
    bin = strtol(binaryIn.UTF8String,NULL,2);
    NSString *oct = [NSString stringWithFormat:@"%1o", bin];
    return oct;
}

//CLEAR ALL TEXTFIELDS
-(void) deleteEveryThing: (NSString *) character{
    if([character isEqualToString:(NSString *)clear]){
       
        [_decimalDisplay setString:[NSString string]];
        [_hexDisplay setString:[NSString string]];
        [_octalDisplay setString:[NSString string]];
        [_binaryDisplay setString:[NSString string]];
    }
}

-(NSString *) octalDisplayValue{
    if([_octalDisplay length]){
        return [[_octalDisplay copy]autorelease];
    }
    else {
        return @"0";
    }
}

-(NSString *) binaryDisplayValue{
    if([_binaryDisplay length]){
        return [[_binaryDisplay copy]autorelease];
    }
    else{
        return @"0";
    }
}

-(NSString *) hexDisplayValue{
    if([_hexDisplay length]){
        return [[_hexDisplay copy]autorelease];
    }
    else {
        return @"0";
    }
}

-(NSString *)decimalDisplayValue {
    if([_decimalDisplay length]){
        return [[_decimalDisplay copy] autorelease];
}
    else {
        return @"0";
    }
}

@end
