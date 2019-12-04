//
//  NSObjectAssociate.swift
//  PHFoundation
//
//  Created by Panghu Lee on 2019/12/4.
//  Copyright © 2019 Panghu Lee. All rights reserved.
//

import Foundation

extension PHFoundationDSL where Target: NSObject {
    
    public func setAssociateValue(_ value: Any?, _ key: UnsafeRawPointer) {
        objc_setAssociatedObject(target, key, value, objc_AssociationPolicy.OBJC_ASSOCIATION_RETAIN_NONATOMIC)
    }
    
    public func setAssociateWeakValue(_ value: Any?, _ key: UnsafeRawPointer) {
        objc_setAssociatedObject(target, key, value, objc_AssociationPolicy.OBJC_ASSOCIATION_ASSIGN)
    }
    
    public func setAssociateCopyValue(_ value: Any?, _ key: UnsafeRawPointer) {
        objc_setAssociatedObject(target, key, value, objc_AssociationPolicy.OBJC_ASSOCIATION_COPY_NONATOMIC)
    }
    
    public func associateValue(_ key: UnsafeRawPointer) -> Any? {
        return objc_getAssociatedObject(target, key)
    }
    
    public func removeAssociatedValues() {
        objc_removeAssociatedObjects(target);
    }
}
