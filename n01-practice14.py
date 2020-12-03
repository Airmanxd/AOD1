
string = 'Паньковецкий Александр Сергеевич'
# класс ячейки
class NodeTree(object):

    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right

    def children(self):
        return (self.left, self.right)

    def nodes(self):
        return (self.left, self.right)

    def __str__(self):
        return '%s_%s' % (self.left, self.right)

#функция непосредственной кодировки строки
def huffman_code_tree(node, left=True, binString=''):
    if type(node) is str:
        return {node: binString}
    (l, r) = node.children()
    d = dict()
    d.update(huffman_code_tree(l, True, binString + '0'))
    d.update(huffman_code_tree(r, False, binString + '1'))
    return d

#подсчет частоты
freq = {}
for c in string:
    if c in freq:
        freq[c] += 1
    else:
        freq[c] = 1
#сортировки частоты по убыванию
freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)

nodes = freq
#построение дерева
while len(nodes) > 1:
    (key1, c1) = nodes[-1]
    (key2, c2) = nodes[-2]
    nodes = nodes[:-2]
    node = NodeTree(key1, key2)
    nodes.append((node, c1 + c2))

    nodes = sorted(nodes, key=lambda x: x[1], reverse=True)

huffmanCode = huffman_code_tree(nodes[0][0])
#вывод таблицы вероятностей
print('Буква  |  Вероятность')
for (char, frequency) in freq:
    print(' %-5r | %8.5f' % (char, (frequency/len(string))))
print('----------------------')

#вывод таблицы кодов
print(' Буква | Кодировка ')
for (char, frequency) in freq:
    print(' %-5r |%12s' % (char, huffmanCode[char]))
print('----------------------')

#подсчет длины закодированной строки
encoded_length = 0
for i in string:
    encoded_length += len(huffmanCode[i])
#подсчет максимальной длины кода, для сравнения с равномерным кодом
max_length = 0
i = 0
for char, frequency in freq:
    temp = len(huffmanCode[char])
    if temp > max_length:
        max_length = temp

length = len(string)

print('Длина закодированной строки: {}'.format(encoded_length))
print('Длина закодированной строки в ASCII: {}'.format(length*8))
print('Длина строки в ровномерном коде: {}'.format(length*max_length))
print('Коэффициент сжатия относительно ASCII: {}'.format(length*8/encoded_length))
print('Коэффициент сжатия относительно ровномерного кода: {}'.format(length*max_length/encoded_length))
print('Средняя длина кода: {}'.format(encoded_length/length))