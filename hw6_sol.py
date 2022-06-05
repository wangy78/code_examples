# -*- coding: utf-8 -*-
"""
Created on Fri Oct 30 12:25:24 2020
this program has 2 parts, the first part is to analuze each of the 2 files and  the second part is to compare them
@author: wangy78
"""
'''
this function takes in the filename and clear everything, speprate by space
replace anything not a letter with '' and  return a new list of only individual words
'''
def phasing(f):
    newtext = []

    con = open(f).readlines()

    for i in list(range(0, len(con))):
        words = con[i].split()

        for w in words:
            
            for char in w:
                
                
                if char.isalpha() and char != 'â':
                    continue
                else:
                    w = w.replace(char, '')
            if len(w)>0:
                newtext.append(w.lower())
    
    return newtext
'''


this function takes in a list of words which is generated by the function above
 remove the common words found in the another textfile and returns a new list of words

'''
def remove_com(f):

    ff = []
    for i in f:

        if i in stopw:            
            continue
        else:
            ff.append(i)
            
        
    return ff
'''
This function find the word lenth rate by adding every letter of a list of words 
and devide by the lenth of the list
'''

def count(l):
    totl= 0
    for i in l:
        for j in i:
            totl+= 1
    wordl = totl/len(l)
    return wordl

'''this function finds the number of ratio between the number of
distinct words and the total number of words.  
creates a set of the list give in the parameter
and finds the difference of the lenth between the two, which is the num of distinct words
then finds the ratio between the number of distinct words and the total number of words. 
'''
def dup_rate(l):
    
    sl = set(l)
    
    num = len(sl)
    rate = num/len(l)
    return rate

'''
finds the word set, takes in a list of words
find words accoarding to word lenth
find the formated space needed
returns a list of lists of words of each lenth, no duplication( formatted if list is longer than 6, only dirst and last 3),
the longest word lenth and a list of lists of words of each lenth, with duplication
'''
def word_set(l):
    lthree = []
    byl = []
    
    i = 1
    lll = 0
    for v in l:
        if len(v)>lll:
            lll= len(v)
    while i < lll+1:
        li = set()
        bb = []
        for word in l:
            if len(word) == i:
                li.add(word)
                bb.append(word)
                
        li = list(li)
        
        li.sort()
       
        space = '   '

        if len(li)<10 and i<10:
            space2 = '  '
        elif len(li)<10 and i>=10:
            space2 = '  '
            space = '  '
        elif len(li)<100 and i <10:
            space2 = ' '
        else:
            space2 = ''
        sml = [space + str(i)+':'+space2,str(len(li))+':']
        if len(li)<7:
            for w in li:
                
                sml.append(w)
        else:
            sml.append(li[0])
            sml.append(li[1])
            sml.append(li[2])
            sml.append('...')
            sml.append(li[len(li)-3])
            sml.append(li[len(li)-2])
            sml.append(li[len(li)-1])
        
        sml = ' '.join(sml)
        lthree.append(sml)
        byl.append(tuple(set(bb)))
        i+=1
        
        
    return lthree, lll, byl
    
'''
takes in the list, lenth of seperation and a number which tells weather to print the pairs of words found
finds a word and the word sep lenth apart and sort them so there ios no duplicat, append them into a set
sep - 1, repeat until sep is 0
prints first and last 5 pairs
return rate of distinct pairs and the list of pairs with duplication

'''
def pair(l, sep, jj):
    ttp = [] 
    lp = set()
    s = 1
    while s < sep+1:
        
        for i in list(range(0, len(l)-s)):
            pair = []
            pair.append(l[i])
            pair.append(l[i+s])
            
     
            pair.sort()
            ttp.append(tuple(pair))
            lp.add(tuple(pair))
    
            lp.add(tuple(pair))
            
            
        s+=1
  
    lp = list(lp)
    lp.sort()
    if jj !=1:
        print('  '+str(len(lp)),'distinct pairs')
        if len(lp)<11:
            for j in lp:
                print('  '+j)
        else:
            h = 0
            while h < 5:
                print(' ',lp[h][0], lp[h][1])
                h+=1
            print('  ...')
            d = 5
            while d >0:
                print(' ',lp[len(lp)- d][0],lp[len(lp)- d][1])
                d-=1
        
    ra = len(lp)/len(ttp)
    return ra, ttp

'''
takes in file and run the function above to clean them up
'''
        
stopw = set(phasing('stop.txt'))

fffile = input('Enter the first file to analyze and compare ==> ').strip()
print(fffile)
ssfile = input('Enter the second file to analyze and compare ==> ').strip()
print(ssfile)
sep = input('Enter the maximum separation between words in a pair ==> ')
print(sep)
sep = int(sep)

ffile = phasing(fffile)
ffile = remove_com(ffile)

sfile = phasing(ssfile)
sfile = remove_com(sfile)

print('')

print('Evaluating document',fffile) 
print('1. Average word length: {0:.2f}'.format(count(ffile)))
print('2. Ratio of distinct words to total words: {0:.3f}'.format(dup_rate(ffile)))
i = 0
print('3. Word sets for document',fffile+':')
while i< word_set(ffile)[1]:
    
    print(word_set(ffile)[0][i])
    i+=1
print('4. Word pairs for document',fffile)
print('5. Ratio of distinct word pairs to total: {0:.3f}'.format(pair(ffile, sep, 0)[0]))




print('')
print('Evaluating document',ssfile) 
print('1. Average word length: {0:.2f}'.format(count(sfile)))
print('2. Ratio of distinct words to total words: {0:.3f}'.format(dup_rate(sfile)))
i = 0
print('3. Word sets for document',ssfile+':')
while i< word_set(sfile)[1]:
    
    print(word_set(sfile)[0][i])
    i+=1
print('4. Word pairs for document',ssfile)
print('5. Ratio of distinct word pairs to total: {0:.3f}'.format(pair(sfile, sep, 0)[0]))

print('')

'''
compare two documents, use the equztion given 
'''
print('Summary comparison')
if count(sfile) > count(ffile):
    print('1.',ssfile,'on average uses longer words than',fffile)
elif count(sfile) < count(ffile):
    print('1.',fffile,'on average uses longer words than',ssfile)
else:
    print('draw')
    
both = set(set(ffile).intersection(set(sfile)))
print('2. Overall word use similarity: {0:.3f}'.format(len(both)/len(set((ffile)+(sfile)))))

print('3. Word use similarity by length:')
b = 1

if word_set(ffile)[1]< word_set(sfile)[1]:
    while b < word_set(sfile)[1]:

        bothl = set(set(word_set(ffile)[2][b-1]).intersection(set(word_set(sfile)[2][b-1])))
        if len(set((word_set(ffile)[2][b-1])+(word_set(sfile)[2][b-1]))) == 0:
            siml = 0
            
        else:
            siml = len(bothl)/len(set((word_set(ffile)[2][b-1])+(word_set(sfile)[2][b-1])))
            
        
        if b > 9:
            ss = '  '
        else:
            ss = '   '
            
        print(ss+str(b)+': {0:.4f}'.format(siml))
        b+=1
    while b < word_set(sfile)[1]+1:
        if b > 9:
            ss = '  '
        else:
            ss = '   '
        print(ss+str(b)+': {0:.4f}'.format(0))
        b+=1
else:
    while b < word_set(ffile)[1]:
        bothl = set(set(word_set(ffile)[2][b-1]).intersection(set(word_set(sfile)[2][b-1])))
        if len(set((word_set(ffile)[2][b-1])+(word_set(sfile)[2][b-1]))) == 0:
            siml = 0
            
        else:
            siml = len(bothl)/len(set((word_set(ffile)[2][b-1])+(word_set(sfile)[2][b-1])))
            
        if b > 9:
            ss = '  '
        else:
            ss = '   '
            
        print(ss+str(b)+': {0:.4f}'.format(siml))
        b+=1
    while b < word_set(ffile)[1]+1:
        if b > 9:
            ss = '  '
        else:
            ss = '   '
        print(ss+str(b)+': {0:.4f}'.format(0))
        b+=1
        
bothp = set(set(pair(sfile, sep, 1)[1]).intersection(set(pair(ffile, sep, 1)[1])))
print('4. Word pair similarity: {0:.4f}'.format(len(bothp)/len(set((pair(sfile, sep, 1)[1])+(pair(ffile, sep, 1)[1])))))



