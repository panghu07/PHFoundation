//
//  AppDelegate.swift
//  Example
//
//  Created by Panghu Lee on 2019/12/4.
//  Copyright © 2019 Panghu Lee. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    
    var window: UIWindow?
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        window = UIWindow(frame: UIScreen.main.bounds)
        window?.rootViewController = NavigationController(rootViewController: UIViewController())
        window?.makeKeyAndVisible()
        return true
    }
}
