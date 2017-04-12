module ReVIEW
  class HTMLBuilder
    def inline_chapref(id)
      title = super
      %Q(<a href="/#{id}#{extname}">#{title}</a>)
    end
  end
  class Builder
    def headline_prefix(level)
	  ['', nil]
    end
  end
  class I18n
    def t(str, args = nil)
      frmt = @store[@locale][str].dup
      frmt.gsub!('%%', '##')

      if !args.is_a?(Array)
        if args.nil? && frmt !~ /\%/
          args = []
        else
          args = [args]
        end
      end

      percents = frmt.scan(/%\w{1,3}/)
      percents.each_with_index do |i, idx|
        case i
        when "%pA"
          frmt.sub!(i, ALPHA_U[args[idx]])
          args.delete idx
        when "%pa"
          frmt.sub!(i, ALPHA_L[args[idx]])
          args.delete idx
        when "%pAW"
          frmt.sub!(i, ALPHA_UW[args[idx]])
          args.delete idx
        when "%paW"
          frmt.sub!(i, ALPHA_LW[args[idx]])
          args.delete idx
        when "%pR"
          frmt.sub!(i, ROMAN_U[args[idx]])
          args.delete idx
        when "%pr"
          frmt.sub!(i, ROMAN_L[args[idx]])
          args.delete idx
        when "%pRW"
          frmt.sub!(i, ROMAN_UW[args[idx]])
          args.delete idx
        when "%pJ"
          frmt.sub!(i, JAPAN[args[idx]])
          args.delete idx
        when "%pdW"
          frmt.sub!(i, ARABIC_LW[args[idx]])
          args.delete idx
        when "%pDW"
          frmt.sub!(i, ARABIC_UW[args[idx]])
          args.delete idx
        end
      end
      frmt.gsub!('##', '%%')
      frmt % args
    rescue
      str
    end
  end
end
