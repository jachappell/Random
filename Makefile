LIBDIR=lib
LIB=$(LIBDIR)/libRandom.a
OBJDIR=.obj
CC=g++
AR=ar

CFLAGS = -Wall -O3 --std=c++1z  -I include

$(shell mkdir -p $(LIBDIR)) 
$(shell mkdir -p $(OBJDIR)) 

OBJS = $(OBJDIR)/Generator.o 

$(LIB) : $(OBJS)
	$(AR) r $(LIB) $(OBJS) 

-include $(OBJS:.o=.d)

$(OBJDIR)/%.o: ./src/%.cpp
	$(CC) -c $(CFLAGS) src/$*.cpp -o $(OBJDIR)/$*.o
	$(CC) -MM $(CFLAGS) src/$*.cpp > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp

clean:
	rm -rf $(LIBDIR) $(OBJDIR) 

