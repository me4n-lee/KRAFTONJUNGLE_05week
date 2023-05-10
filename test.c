LEFT-ROTATE(t, x)
    
    y = x.right // y를 설정
    x.right = y.left // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 옮기는 과정

    if y.left != t.nil
        y.left.p = x
    
    y.p = x.p // x의 부모를 y로 연결

    if x.lp == t,nil
        t.root = y
    elseif x == x.p.left
        x.p.left = y
    else
        x.p.right = y
    
    y.left = x // x를 y의 왼쪽으로 놓는 과정
    x.p = y

/*------------------------------------------------------*/

RB-INSERT(t, z)

    y = t.nil
    x = t.root

    while x != t.nil
        y = x

        if z.key < x.key
            x = x.left
        else
            x = x.right
    
    z.p = y

    if y == t.nil
        t.root = z
    elseif z.key < y.key
        y.left = z
    else
        y.right = z

    z.left = t.nil
    z.right = t.nil
    z.color = RED

    RB-INSERT-FIXUP(t, z)


RB-INSERT-FIXUP(t, z)

    while z.p.color == RED
        if z.p == z.p.p.left
            y = z.p.p.right
            
            if y.color == RED 
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            else
                if z == z.p.right
                    z = z.p
                    LEFT-ROTATE(t, z)

                z.p.color = BLACK
                z.p.p.color = RED
                RIGHT-ROTATE(t, z.p.p)

        else // z.p is the right child of z.p.p
            y = z.p.p.left

            if y.color == RED:
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            else:
                if z == z.p.left:
                    z = z.p
                    RIGHT-ROTATE(t, z)

                z.p.color = BLACK
                z.p.p.color = RED
                LEFT-ROTATE(t, z.p.p)
    
    t.root.color = BLACK

/*------------------------------------------------------*/

RB-TRANSPLANT(t, u, v)

    if u.p == t.nil
        t.root = v
    else if u == u.p.left
        u.p.left = v
    else
        u.p.right = v
    
    v.p = u.p


RB-DELETE(t,z)

    y = z
    y-original-color = y.color

    if z.left = t.nil
        x = z.right
        RB-TRANSPLANT(t, z, z.right)
    elseif z.right == t.nil
        x = z.left
        RB-TRANSPLANT(t, z, z.left)
    else
        y= TREE-MIN(z.right)
        y-original-color = y.color
        x = y.right
        
        if y.p == z
            x.p = y
        else
            RB-TRANSPLANT(t, y, y.right)
            y.right = z.right
            y.right.p = y
        
        RB-TRANSPLANT(t, z, y)
        y.left = z.left
        y.right.p = y
        y.color = z.color

    if y-original-color == BLACK
        RB-DELETE-FIXUP(t, x)


RB-DELETE-FIXUP(t, x)

    while x != t.root and x.color == BLACK
        if x == x.p.left
            w = x.p.right
            
            if w.color == RED
                w.color = BLACK
                x.p.color = RED
                LEFT-ROTATE(t, x.p)
                w = x.p.right

            if w.left.color == BLACK and w.right.color == BLACK
                w.color = RED
                x = x.p
            else 
                if w.right.color == BLACK
                    w.left.color = BLACK
                    w.color = RED
                    RIGHT-ROTATE(t, w)
                    w = x.p.right
                
                w.color = x.p.color
                x.p.color = BLACK
                w.right.color = BLACK
                LEFT-ROTATE(t, x.p)
                x = t.root

        else // x is the right child of its parent
            w = x.p.left

            if w.color == RED
                w.color = BLACK
                x.p.color = RED
                RIGHT-ROTATE(t, x.p)
                w = x.p.left

            if w.right.color == BLACK and w.left.color == BLACK
                w.color = RED
                x = x.p
            else 
                if w.left.color == BLACK
                    w.right.color = BLACK
                    w.color = RED
                    LEFT-ROTATE(t, w)
                    w = x.p.left

                w.color = x.p.color
                x.p.color = BLACK
                w.left.color = BLACK
                RIGHT-ROTATE(t, x.p)
                x = t.root

    x.color = BLACK

