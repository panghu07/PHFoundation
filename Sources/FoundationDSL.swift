//
//  FoundationDSL.swift
//  PHFoundation
//
//  Created by Panghu Lee on 2019/12/4.
//  Copyright © 2019 Panghu Lee. All rights reserved.
//

public struct PHFoundationDSL<Target> {
    
    public let target: Target
    
    public init(_ target: Target) {
        self.target = target
    }
}

public protocol PHFoundationCompatible {
    
    associatedtype CompatibleType
    
    var ph: PHFoundationDSL<CompatibleType> { get set }
    static var ph: PHFoundationDSL<CompatibleType>.Type { get set }
}

extension PHFoundationCompatible {
    
    public var ph: PHFoundationDSL<Self> {
        get { return PHFoundationDSL(self) }
        set { }
    }
    
    public static var ph: PHFoundationDSL<Self>.Type {
        get { return PHFoundationDSL<Self>.self }
        set { }
    }
}

import class Foundation.NSObject

extension NSObject: PHFoundationCompatible { }
