class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def preorder(self, root):
        if not root:
            return []
        return [root.val] + self.preorder(root.left) + self.preorder(root.right)
    
    def inorder(self, root):
        if not root:
            return []
        return self.inorder(root.left) + [root.val] + self.inorder(root.right)

    def postorder(self, root):
        if not root:
            return []
        return self.postorder(root.left) + self.postorder(root.right) + [root.val]

    def preorder_iterative(self, root):
        if not root:
            return []
        stack, res = [root], []
        while stack:
            node = stack.pop()
            res.append(node.val)
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
        return res
    
    def inorder_iterative(self, root):
        if not root:
            return []
        stack, res = [], []
        node = root
        while stack or node:
            while node:
                stack.append(node)
                node = node.left
            node = stack.pop()
            res.append(node.val)
            node = node.right
        return res
    
    def postorder_iterative(self, root):
        if not root:
            return []
        stack, res = [root], []
        while stack:
            node = stack.pop()
            res.append(node.val)
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)
        return res[::-1]
    
    def postorder_iterative2(self, root):
        if not root:
            return []
        stack1, stack2, res = [root], [], []
        while stack1:
            node = stack1.pop()
            stack2.append((node))
            if node.left:
                stack1.append(node.left)
            if node.right:
                stack1.append(node.right)
        while stack2:
            node = stack2.pop()
            res.append(node.val)
        return res
    
    def postorder_iterative3(self, root):
        if not root:
            return []
        stack, res = [], []
        stack.append((root, False))
        while stack:
            node, visited = stack.pop()
            if node:
                if visited:
                    res.append(node.val)
                else:
                    stack.append((node, True))
                    stack.append((node.right,False))
                    stack.append((node.left, False))
        return res
    
    def postorder_iterative4(self, root):
        if not root:
            return []
        stack, res = [], []
        cur, prev = root, None
        while stack or cur:
            while cur:
                stack.append(cur)
                cur = cur.left
            if(not cur.right or not prev == cur.right):


            

    